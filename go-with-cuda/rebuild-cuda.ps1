& nvcc cuda/maxmul.cu -o lib/maxmul.dll --shared
Copy-Item lib/maxmul.dll maxmul.dll