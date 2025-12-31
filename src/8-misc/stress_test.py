from subprocess import run

# what: stress test driver (input -> naive vs solve).
# usage: keep input.cpp/naive.cpp/solve.cpp and run python3 stress_test.py

def build(cmd):
    run(cmd, shell=True, check=True)


def exec_bin(bin_path, inp):
    return run([bin_path], capture_output=True, input=inp, text=True).stdout


build("g++ -std=c++17 -O2 -pipe input.cpp -o input")
build("g++ -std=c++17 -O2 -pipe naive.cpp -o naive")
build("g++ -std=c++17 -O2 -pipe solve.cpp -o solve")

for it in range(100000):
    inp = exec_bin("./input", str(it))
    o1 = exec_bin("./naive", inp)
    o2 = exec_bin("./solve", inp)
    if o1 != o2:
        print(inp)
        print("output_naive")
        print(o1)
        print("output_solve")
        print(o2)
        break
