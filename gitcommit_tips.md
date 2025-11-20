in scenarion 1, skipping git add and just doing git commit wil return an error because you did not add any file to be commited. and you would not be able to push it because need to have a commit before you can push. in scenario 2 running git add would work. but skipping git commit and running git push would return an error because there is no commits to be pushed. on git hub, no changes would happen in scenaio 1, and with git status we see:On branch main
Changes not staged for commit:
  modified: gitoffline.md.

it would be the same for secenario 2 on git hub, but on the git status we see
 On branch main
Changes to be committed:
  modified: gitoffline.md.

to fix this issue we just have to make sure we follow all the steps
