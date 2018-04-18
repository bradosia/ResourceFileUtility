namespace ResourceFileUtility {
    using System.Runtime.InteropServices;
    using System;

    class Loader {
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int math_add(int a, int b);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int math_add2(int a, int b);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void coutTest();
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern IntPtr compile_new();
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void objSet(IntPtr ptr, int testint);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int objGet(IntPtr ptr);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void compile_info(IntPtr ptr, String fileName);
    }

    public class Compiler {
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int math_add(int a, int b);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int math_add2(int a, int b);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void coutTest();
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern IntPtr compile_new();
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void objSet(IntPtr ptr, int testint);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int objGet(IntPtr ptr);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void compile_info(IntPtr ptr, string fileName);

        private IntPtr objPtr;

        public Compiler() {
            objPtr = compile_new();
        }
        public IntPtr ptr() {
            return objPtr;
        }
        public void info(IntPtr ptr, string fileName) {
            compile_info(ptr, fileName);
        }
    }

    class Stream {
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
    }
}