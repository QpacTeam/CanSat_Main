import time


def timer(function):
    def wrapper(*args, **kwargs):
        act_time: float = time.time()
        function(*args, **kwargs)
        delta_time: float = time.time() - act_time
        print(f"{function} -> {delta_time}")

    # new line of code

    return wrapper
