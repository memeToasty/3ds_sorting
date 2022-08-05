# 3ds_sorting
Visualisation of some sorting algorithms on the Nintendo 3DS
# Build
## Requirements
- [devkitARM](https://devkitpro.org/wiki/Getting_Started)
### Building the CIA application
- [`makerom`](https://github.com/3DSGuy/Project_CTR/releases/tag/makerom-v0.18.3)
- [`bannertool`](https://github.com/Steveice10/bannertool/releases/tag/1.2.0)
### "Auto"-Deployment
- `lftp`
    - `sudo apt install lftp`
- [ftpd](https://github.com/mtheall/ftpd): A FTP server on the Nintendo 3DS
## Building
### .3dsx
`make`
### .cia
`./build.sh`
## Deployment
Replace `USERNAME`, `PASSWORD`, `IP` and `PORT` in the `deploy.sh.example`
```
mv deploy.sh.example deploy.sh
./deploy.sh
```
## Usage


# Credits
- [PUREBEATS](https://www.youtube.com/PUREBEATS "YouTube PUREBEATS") for the amazing Jingle
- [Tom](https://github.com/TomRomeo "GitHub Tom") for the help with the 3D-modeling
