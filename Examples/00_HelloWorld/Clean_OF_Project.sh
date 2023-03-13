#!/bin/bash

# Clean_OF_Project.sh :
# This script cleans the OF VS Project folder.
# Then we need to re run the OF Project Generator.

echo "RUNNING SCRIPT TO REMOVE PROJECT FILES."
echo "Then we need to re run the OF Project Generator."

# Get dir
folder_path="$(dirname "$0")"

# List
find "$folder_path" -type d | while read folder; do
    echo "$folder"
done

# Removing .vs y obj
echo "Removing /.vs and /obj..."
if ! find "$folder_path" \( -name ".vs" -o -name "obj" \) -type d -exec rm -r "{}" \; ; then
    echo "Error: Could not find .vs or obj directory."
fi

# Remove .sln, .vcxproj, .filters, .user
if ! find . \( -iname "*.sln" -o -iname "*.vcxproj" -o -iname "*.filters" -o -iname "*.user" \) -type f -delete ; then
    echo "Error: Could not find Visual Studio project files."
fi
echo "Removed VS Project files."

# # Clean bin
# echo "Clean /bin. Remove /bin files.. except '/bin/data/'"
# cd "$folder_path/bin"
# if ! find . -type f ! -name 'data' -delete ; then
#     echo "Error: Could not delete files from /bin directory."
# fi

# # Clean bin/data
# echo "Clean /bin/data. Remove all except '/bin/data/assets/'"
# cd "$folder_path/bin/data/"
# if ! find . ! -name 'assets' -delete ; then
#     echo "Error: Could not delete files from /bin/data directory."
# fi

# back
cd "$folder_path"

echo "Done!"
