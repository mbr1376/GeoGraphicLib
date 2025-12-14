import ctypes
lib = ctypes.CDLL('lib/libGeoWrapper.so')



def distance(lat1, lon1, lat2, lon2):
    lib.Distance.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]
    lib.Distance.restype = ctypes.c_double
    return lib.Distance(lat1, lon1, lat2, lon2)
    
if __name__ == "__main__":
    lat1, lon1 = 34.0522, -118.2437  # Los Angeles
    lat2, lon2 = 40.7128, -74.0060   # New York City
    dist = distance(lat1, lon1, lat2, lon2)
    print(f"Distance between LA and NYC: {dist} km")