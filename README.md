# dwm - dynamic window manager
This is my build for dwm, an extremely fast, small, and dynamic window manager for X.

Since this is suckless, documentation is source code :v 

## Included patches   
- center
- colorbar
- fullgaps
- statuspadding
- noborder
- xrdb*
- fullscreen
- systray
- warp
- focusonactive
- ewmhtags
- autostart
- dynamicswallow

The xrdb patch was modified to access all the avaliable colors, useful if you use pywal for example.

## Installation
```sh 
sudo make clean install
```

## Requirements
This build assumes you have a version o `libxft` with support to colored emojis ( `libxft-bgra` on the AUR for example)
