git pull

for package in `find ${PWD} -maxdepth 1 -mindepth 1 -type d | grep -v git`; do
    cd ${package} && make && cd ..
done
