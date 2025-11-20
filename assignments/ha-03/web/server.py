#!/usr/bin/env python3
from http.server import HTTPServer, SimpleHTTPRequestHandler
import subprocess
import json
import sys
from pathlib import Path

# global variable to hold the C++ process
cpp_process = None

def start_cpp_process():
    global cpp_process
    binary = Path('../src/calc')
    if not Path(binary).exists():
        print(f'ERROR: "{binary}" not found.')
        sys.exit(1)
    cpp_process = subprocess.Popen([binary], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, bufsize=1)
    print('> C++ calculator process started')

class CalcHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        content_types = {'.html': 'text/html', '.css': 'text/css', '.js': 'application/javascript', '.json': 'application/json'}
        path = Path(self.path.lstrip('/') or 'index.html')
        try:
            content_type = content_types.get(path.suffix, 'text/plain')
            self._send_response(200, content_type, path.read_bytes())
        except FileNotFoundError:
            self.send_response(404)
            self.end_headers()
            print(f'Not found: {path}')

    def _send_response(self, status, ctype, data):
        self.send_response(status)
        self.send_header('Content-Type', ctype)
        self.send_header('Content-Length', len(data))
        self.end_headers()
        self.wfile.write(data)

    def do_POST(self):
        global cpp_process
        try:
            if cpp_process.poll() is not None:
                print('C++ process died, restarting ...')
                start_cpp_process()
            # parse request
            content_length = int(self.headers.get('Content-Length', 0))
            data = json.loads(self.rfile.read(content_length))
            mode = data.get('mode', '')
            expression = data.get('expression', '')
            print(f'mode={mode}, expr={expression}')
            # send to C++ process and get result
            cpp_process.stdin.write(f'{mode}|{expression}\n')
            cpp_process.stdin.flush()
            result_line = cpp_process.stdout.readline().strip()
            if not result_line:
                raise RuntimeError('No response from C++ process')
            try:
                result = int(result_line)
            except ValueError:
                raise RuntimeError(result_line)
            print(f'>> {result}')
            self._send_response(200, 'application/json', json.dumps({'result': result}).encode())
        except Exception as e:
            print(e)
            self._send_response(500, 'application/json', json.dumps({'error': str(e)}).encode())
    
    def do_OPTIONS(self):
        self.send_response(200)
        self.end_headers()
    
    def end_headers(self):
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'POST, GET, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        super().end_headers()

def main():
    if not Path('./index.html').exists():
        print("ERROR: index.html not found in current directory")
        sys.exit(1)
    
    # start C++ and HTTP servers
    start_cpp_process()
    server = HTTPServer(('localhost', 8080), CalcHandler)
    print('Server running on http://localhost:8080')
    print('Press Ctrl+C to stop')
    
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print('\n\nShutting down ...')
        if cpp_process:
            cpp_process.terminate()
            cpp_process.wait()
        print('Server stopped')

if __name__ == '__main__':
    main()