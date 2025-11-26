#emcc leak.c -o index.js -s EXPORTED_FUNCTIONS="['_leak_mb', '_main']" -s WASM=1 -s EXPORTED_RUNTIME_METHODS="['ccall']"
emcc leak.c -o index.js -s EXPORTED_FUNCTIONS="['_leak_mb']" -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS="['ccall']" -s INITIAL_MEMORY=134217728 -s ALLOW_MEMORY_GROWTH=1
