Программа для обнаружения лишних предметов (например, руки) в рабочей зоне манипулятора

Запуск:
```
cd build
cmake ..
make
./main
```


Установка OpenCV:
```
https://medium.com/analytics-vidhya/how-to-install-opencv-for-visual-studio-code-using-ubuntu-os-9398b2f32d53
```
Установка BGSLibrary:
```
git clone --recursive https://github.com/andrewssobral/bgslibrary.git
cd build
cmake ..
make -j $(nproc)
make install
```
