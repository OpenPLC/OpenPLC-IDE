# you need to have astyle installed before running this
find libraries/ hardware/ -name '*.ino' -exec astyle --options=build/shared/lib/formatter.conf {} \;


find hardware/openplc/ -name '*.ino' -exec astyle --options=build/shared/lib/formatter.conf {} \;
find hardware/openplc/ -name '*.h' -exec astyle --options=build/shared/lib/formatter.conf {} \;
find hardware/openplc/ -name '*.c' -exec astyle --options=build/shared/lib/formatter.conf {} \;
find hardware/openplc/ -name '*.hpp' -exec astyle --options=build/shared/lib/formatter.conf {} \;
find hardware/openplc/ -name '*.cpp' -exec astyle --options=build/shared/lib/formatter.conf {} \;

find hardware/openplc/ -name '*.orig' -exec rm -rfv {} \;

