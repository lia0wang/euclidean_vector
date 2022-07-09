for file in source/*.cpp test/*.cpp test/euclidean_vector/*.cpp include/comp6771/*.hpp; do
    clang-format-11 -style=file -i $file
done