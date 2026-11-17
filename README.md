# SMG2 BgmChangeObj

## BgmChangeObj in SMG2

An object that allows changing between two music tracks based on switches.

Below is a list of everything that's included:
- The BgmChangeObj object for placing down in a level editor.

Below is a list of other things that you will need:
- A level editor.
- Two entries for your level inside StageBgmInfo.bcsv.
> *Note: Don't forget that your level has to be inside StageBgmInfo as well as ScenarioBgmInfo.*

BgmChangeObj aims to create a feature that is otherwise not possible via BgmChangeArea. It should not be used as a replacement.

## Credits
- @superhackio

## Setup
BgmChangeObj uses similar parameters to BgmChangeArea, however doesn't support all modes. Obj_args 0 through 2 define the music to be played when SW_A is activated. When deactivated, obj_args 3 through 5 will take effect.

### BgmChangeObj
| Parameter | Description |
| --- | --- |
| Obj_arg0 | Change Type A. The mode for changing music. Only mode 1 is supported (Fade-out and change song). |
| Obj_arg1 | Fade Time A. The time in frames it takes for the previously playing music to fade out. |
| Obj_arg2 | StageBgmInfo Column A. The column in StageBgmInfo that defines which music to play next. This is NOT the same as the number inside the column header (ChangeBgmIdNameX). |
| Obj_arg3 | Change Type B. Same as Obj_arg0. |
| Obj_arg4 | Fade Time B. Same as Obj_arg1. |
| Obj_arg5 | StageBgmInfo Column B. Same as Obj_arg2. |
| SW_A | When activated, Obj_args 0 through 2 will take effect. Once deactivated, Obj_args 3 through 5 will take effect. This can be repeated multiple times. |
