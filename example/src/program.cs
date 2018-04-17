namespace HighSpeedMathTest {
    using System.Runtime.InteropServices;
    using System;

    class Program {
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int math_add(int a, int b);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int math_add2(int a, int b);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void coutTest();
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern IntPtr objNew();
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void objSet(IntPtr ptr, int testint);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int objGet(IntPtr ptr);

        static void Main(string[] args) {
            int result = math_add(27, 28);
            Console.WriteLine(result);
            result = math_add2(27, 28);
            Console.WriteLine(result);
            coutTest();
            IntPtr objPtr = objNew();
            Console.WriteLine(objPtr);
            objSet(objPtr, 6);
            int testint = objGet(objPtr);
            Console.WriteLine(testint);

            // Keep the console window open in debug mode.
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}