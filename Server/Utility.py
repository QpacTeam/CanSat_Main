import time

def timer(function):
    def wrapper(*args, **kwargs):
        act_time = time.time()
        function(*args, **kwargs)
        delta_time = time.time() - act_time
        print(f"{function} :: {delta_time}")
    return wrapper