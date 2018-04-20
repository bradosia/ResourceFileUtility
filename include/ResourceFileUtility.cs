namespace ResourceFileUtility {
    using System.Runtime.InteropServices;
    using System;

    public abstract class CallbackHandler {
        public abstract void fileComplete(string filePath);
        public abstract void packComplete();
    }

    class Loader {
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern IntPtr loader_new();

        private IntPtr thisPtr;

        public Loader() {
            thisPtr = loader_new();
        }
        public IntPtr ptr() {
            return thisPtr;
        }
    }

    public class Compiler {
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern IntPtr compiler_new();
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void compiler_info(IntPtr ptr, string fileName);
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void compiler_pack(IntPtr ptr, string fileName);



        private IntPtr thisPtr;

        public Compiler() {
            thisPtr = compiler_new();
        }
        public IntPtr ptr() {
            return thisPtr;
        }
        public void info(string fileName) {
            compiler_info(thisPtr, fileName);
        }
        public void pack(string fileName) {
            compiler_pack(thisPtr, fileName);
        }
        public void pack(string fileName, CallbackHandler cb) {
            // how do you handle the callback?
            compiler_pack(thisPtr, fileName);
        }

    }

    class Stream {
        [DllImport("ResourceFileUtility.dll", CallingConvention = CallingConvention.StdCall)]
        static extern IntPtr stream_new();

        private IntPtr thisPtr;

        public Stream() {
            thisPtr = stream_new();
        }
        public IntPtr ptr() {
            return thisPtr;
        }
    }
}