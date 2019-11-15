#!/bin/bash
# Create .dmg file for macOS

APP_VERS="1.3"
DMG_NAME="AZ-StateMachine_v${APP_VERS}_macos"
OUTPUT_DMG_DIR="../Downloads"

# The directory of the script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# The temp directory used, within $DIR
WORK_DIR=`mktemp -d "${DIR}/tmp"`
#echo "DIR="$DIR
#echo "WORK_DIR="$WORK_DIR

# Check if tmp dir was created
if [[ ! "${WORK_DIR}" || ! -d "${WORK_DIR}" ]]; then
    echo "Could not create temp dir"
    exit 1
fi

# Function to deletes the temp directory
function cleanup {
    rm -rf "${WORK_DIR}"
    #echo "Deleted temp working directory ${WORK_DIR}"
}

# Register the cleanup function to be called on the EXIT signal
trap cleanup EXIT

# Copy application on temp dir
cp -R "../Generator/bin/release/macx/AZ-StateMachine-Generator.app" "${WORK_DIR}"
# Copy XML examples
mkdir "${WORK_DIR}/Examples"
cp ../Examples/*.xml "${WORK_DIR}/Examples"
# Copy other files without hidden files
rsync -a --exclude=".*" "../Engine" "${WORK_DIR}"

# Create .dmg
hdiutil create -volname "${DMG_NAME}" -srcfolder "${WORK_DIR}" -ov -format UDZO "${OUTPUT_DMG_DIR}/${DMG_NAME}.dmg"
