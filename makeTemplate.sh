set -x

if [ -z "${1}" ]; then
    echo "Please enter destination directory!"
    set +x && return
fi

if [ -d "${1}" ]; then
    echo "Directory ${1} already exists!"
    set +x && return
fi

mkdir ${1} && rsync --progress -av template/ ${1}/
sed -i.bak "s|helloWorld|${1}|" ${1}/Makefile && rm ${1}/Makefile.bak

set +x
