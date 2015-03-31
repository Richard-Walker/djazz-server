

#
# Decorator to make a function asynchronous
# The decorated function returns the created process
#
def asyncFunc(func):
    """
        asyncFunc(func)
            function decorator, intended to make "func" run in a separate
            thread (asynchronously).
            Returns the created Thread object

            E.g.:
            @run_async
            def task1():
                do_something

            @run_async
            def task2():
                do_something_too

            t1 = task1()
            t2 = task2()
            ...
            t1.join()
            t2.join()
    """
    from threading import Thread
    from functools import wraps

    @wraps(func)
    def async_func(*args, **kwargs):
        func_hl = Thread(target=func, args=args, kwargs=kwargs)
        func_hl.start()
        return func_hl

    return async_func


#
# Iterator that makes <count> time lapses of <duration> seconds
# Works by waiting some time before yielding the next item
# The yielded item is the new lapse end datetime (timestamp)
#
def timeLapses(duration, count):
    from time import time, sleep
    nextTime = time()
    yield nextTime
    for i in range(1, count):
        nextTime += duration
        timeToSleep = nextTime - time()
        if timeToSleep > 0:
            sleep(timeToSleep)
        yield nextTime
