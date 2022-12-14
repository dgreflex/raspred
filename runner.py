import sys
import os

if __name__ == '__main__':
    testSize = 1000
    if len(sys.argv) > 1:
        testSize = int(sys.argv[1])
    
    with open("Result.csv", "w") as out_file:
        out_file.write("test_size,result\n")
        for test in range(testSize + 1):
            print(test)
            os.system(f"mpirun --oversubscribe -n 26 ./main {test} > res.tmp")
            with open("res.tmp", "r") as result_file:
                result = result_file.read().split("Result: ")[1]
                out_file.write(f"{test},{int(result) + 100}\n")

    print("Done")