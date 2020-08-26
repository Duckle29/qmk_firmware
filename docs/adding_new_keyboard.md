# Adding a new keyboard to QMK

This guide assumes you have designed a new keyboard, or ported / reverse engineered the matrix of an existing board, and want to add support for it in QMK.

The guide will be based on the following example in kicad

![testboardio_sch](placeholder_sch.png)
![testboardio_brd](placeholder_brd.png)

## Step 0: Set up QMK locally
First, make sure you have a working installtion of qmk by following the [setup guide](https://docs.qmk.fm/#/newbs_getting_started), however make sure to use `qmk setup` with your fork of the main repository as noted in the info box of step 3.

Once your local qmk_firmware repository has been set up, verify that you have both qmk and your repositories registered as remotes with

```bash
git remote -v
> upstream	https://github.com/qmk/qmk_firmware.git (fetch)
> upstream	https://github.com/qmk/qmk_firmware.git (push)
> origin	https://github.com/<you>/qmk_firmware.git (fetch)
> origin	https://github.com/<you>/qmk_firmware.git (push)
```

once you verify that origin points to your fork, and upstream points to the main qmk repository, you should be ready to go. Make sure that you have read about our [Git best practices](https://docs.qmk.fm/#/newbs_git_best_practices)

## Step 2: Make a new keyboard in qmk
In order to make a new keyboard, use the utility script for this by invoking:

```bash
util/new_keyboard.sh
```
And follow the instructions. Once this is done, a new folder will have been created in 
