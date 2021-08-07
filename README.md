# lea

A utility programming language.

'lea' means 'learn'! I just want to write light-weight programming language to help me complete some simple tasks!

I hope i can insist on accomplishing the project!

At present, this isn't a completed project. So, it's unnecessary to download the project!

## build

Now, you can just build parsing program of 'lea' language! And this will go on for a long time. 

If the compiler/interpreter program is finished, I will update the abstract of the README.

```shell
make       # build parsing program - lea
make clean # remove cache files
```

## syntax verify

```shell
make       # build first
cat ./grammarSupport.lea | ./lea
# observe the last segment:
# "Grammar error : ..."     represents failed!
# "Grammar parsed success." represents success!
```
