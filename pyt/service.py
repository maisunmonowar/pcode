import test1
import test2
import test3

def service_func():
    print("service func")

if __name__ == '__main__':
    # service.py executed as script
    # do something
    service_func()
    test1.some_func()
    test2.test2_func()
    test3.test3_func()