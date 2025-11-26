emcc check.c -o index.js -s EXPORTED_FUNCTIONS="['_check_number', '_main']" -s WASM=1 -s EXPORTED_RUNTIME_METHODS="['ccall']"
