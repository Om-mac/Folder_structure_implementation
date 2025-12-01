for f in "$@"; do
    /usr/local/bin/folder_viewer "$f" >/dev/null 2>&1 &
done
