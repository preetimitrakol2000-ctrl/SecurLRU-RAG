import ctypes
import os
import sys

class LruCacheBridge:
    def __init__(self, capacity: int):
        if not os.path.exists("./liblru.so") and not os.path.exists("./liblru.dll"):
            if sys.platform.startswith("win"):
                os.system("gcc -shared -o liblru.dll lru_cache.c")
                lib_path = "./liblru.dll"
            else:
                os.system("gcc -shared -fPIC -o liblru.so lru_cache.c")
                lib_path = "./liblru.so"
        else:
            lib_path = "./liblru.dll" if sys.platform.startswith("win") else "./liblru.so"

        self.lib = ctypes.CDLL(lib_path)
        self.lib.init_lru.restype = ctypes.c_void_p
        self.lib.get_cached_context.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.get_cached_context.restype = ctypes.c_char_p
        self.lib.put_cached_context.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.free_lru.argtypes = [ctypes.c_void_p]
        
        self.cache_ptr = self.lib.init_lru(capacity)

    def fetch_context(self, event_id: str) -> str:
        return self.lib.get_cached_context(self.cache_ptr, event_id.encode('utf-8')).decode('utf-8')

    def push_context(self, event_id: str, document_text: str):
        self.lib.put_cached_context(self.cache_ptr, event_id.encode('utf-8'), document_text.encode('utf-8'))

    def __del__(self):
        if hasattr(self, 'lib') and self.cache_ptr:
            self.lib.free_lru(self.cache_ptr)
