from subprocess import run

run(["g++ input.cpp -o input"], shell=True)
run(["g++ naive.cpp -o naive"], shell=True)
run(["g++ solve.cpp -o solve"], shell=True)
for _ in range(100000):
    inp = run(
        ["./input"], shell=True, capture_output=True, input=str(_), text=True
    ).stdout
    O1 = run(["./naive"], shell=True, capture_output=True, input=inp, text=True).stdout
    O2 = run(["./solve"], shell=True, capture_output=True, input=inp, text=True).stdout
    if O1 != O2:
        print(inp)
        print("output_naive")
        print(O1)
        print("output_solve")
        print(O2)
        break
