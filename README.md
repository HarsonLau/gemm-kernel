# gemm-kernel
这是一个简单的矩阵乘法的实现，主要是为了学习 x86-64 AVX2 指令集的使用。
- 实现了一个基于RAW 依赖的汇编micro benchmark 以测试指令延迟。
- 实现了一个基于无依赖指令流的汇编micro benchmark 以测试指令吞吐量。
- 实现了一个使用3x4 寄存器分块的gemm kernel，达到了96.78%的实际峰值。

## build

```bash
./build.sh
```

## run

```bash
./build/latency_test [cpuid] [looptime] [frequency]
./build/throughput_test [cpuid] [looptime]
./build/main [cpuid] [looptime]
```
## performance

使用"Intel(R) Xeon(R) Gold 6226R CPU @ 2.90GHz" CPU  经测试实际浮点峰值 98.91GFLOPS。
gemm kernel 在 K=128 ，loop time 等于 10000000事， 性能为95.73GFLOPS。达到了实际峰值的96.78%。
