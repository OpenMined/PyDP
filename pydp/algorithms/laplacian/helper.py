def map_type_str(type):
    if type == "int":
        return "Int"
    elif type == "float":
        return "Double"
    else:
        raise RuntimeError(f"dtype: {dtype} is not supported")