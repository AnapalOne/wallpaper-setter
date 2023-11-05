#!/bin/bash

wallpaper_dir="$1"
wallpaperList=./wallpaperList.txt

# delete wallpaperList.txt if it exists just to make sure
if [[ -e $wallpaperList ]]; then
    rm $wallpaperList
fi

for i in $wallpaper_dir/*; do
    if [[ -d $i ]]; then
        continue
    fi
    echo "$i" >> $wallpaperList
done