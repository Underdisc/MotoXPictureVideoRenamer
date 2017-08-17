
# MotoXPictureVideoRenamer
This will rename all of the image and video files from the Moto-X into a more readable format.


## Starting and Ending Formats.

The left side represents the file name at the start and the right is the ending filename.
```
IMG_20170206_035112408.jpg -> 2017-02-06_0.jpg
IMG_20170206_035255124.jpg -> 2017-02-06_0.jpg
```

Videos are slightly different.
```
VID_20170206_035112408.mp4 -> 2017-02-06_0.mp4
VID_20170206_035255124.mp4 -> 2017-02-06_0.mp4
```

## Compile line

g++ motoxrename.cpp -o motoxrename.exe

## Usage

1. Make sure to separate all of the videos from the images into separate directories.
2. Run the program on a directory containing videos or images. `./motoxrename.exe [DIRECTORY]``

## Example

`./motoxrename.exe Images`
Will rename all images in the *Images/* directory.
