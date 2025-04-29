if [ $# -lt 1 ]; then
    echo "Usage: ./run.sh filename (without .cpp)"
    exit 1
fi

NAME=$1

echo "Compiling..."
g++ "$NAME.cpp" -Wall -Wl,--stack=1073741824 -O2 -std=c++20 -lstdc++exp -D LOCAL -o "$NAME"
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

> "$NAME.out"

echo "Running..."
START=$(date +%s%3N)

if [ -f "$NAME.in" ]; then
    ./"$NAME" < "$NAME.in" > "$NAME.out"
else
    ./"$NAME"
fi

RUN_STATUS=$?
END=$(date +%s%3N)
DURATION_MS=$((END - START))

if [ $RUN_STATUS -ne 0 ]; then
    echo "Runtime error (exit code: $RUN_STATUS)"
else
    echo "Execution time: ${DURATION_MS} ms"
fi

rm "$NAME"
