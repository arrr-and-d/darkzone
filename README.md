# Darkzone
A fast and flexible screen dimmer for Windows

Darkzone is a screen dimmer **overlay window** that can be moved and resized to darken the desired area or "zone" of your screen. The application is designed for gamers & streamers. 
The opacity or "darkness" of the Darkzone overlay window can be adjusted using keyboard shortcuts while in focus.

Darkzone is implemented using the native and low level Win32 API for maximum performance. 
The utilized system resources are negligible.

## Screenshots
![image](https://github.com/user-attachments/assets/b7e1fb23-bde3-4074-a0d6-3ab1465d6e82)


## Installation 
Open the Visual Studio solution file and run the project by pressing `CTRL`+`F5`.

Pre-built binaries will be provided through GitHub releases once the application matures.

## Shortcuts
The darzone window needs to be focused to use shortcuts

### Table of shortcuts
| Key | Function | 
| --- | --- |
| `O` / `P`| Decrease / increase window opacity |
| `ARROW LEFT` / `ARROW RIGHT`| Increase / decrease window width |
| `ARROW DOWN` / `ARROW UP`| Increase / decrease window height |
| `RMB Click & drag` / `LMB Click & drag` | Move darkzone |

## Performance / Requirements
Thanks to the low level nature of the Win32 API, 
this application uses just under 1.3 MB of RAM on average.

## Support
If you experience any bugs create a new issue on this repository.
