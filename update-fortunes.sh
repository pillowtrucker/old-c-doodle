#!/usr/bin/env bash
command -v curl >/dev/null 2>&1 || { echo Install curl to update fart fortunes.; exit 1; }
curlver=$(curl --version)
curlver=${curlver#curl }
curlver=${curlver%% (*}
if [ $curlver = "`echo -e "7.68.0\n$curlver" | sort -V | tail -n1`" ]
   then
     curl -v -o fart --etag-compare lastfart --etag-save lastfart http://www.asciiartfarts.com/fortune.txt
else
    while read lastfart;do curl -v -o fart --header "If-None-Match: \"$lastfart\"" http://www.asciiartfarts.com/fortune.txt;done<lastfart
fi
