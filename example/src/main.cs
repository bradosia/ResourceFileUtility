namespace ExampleProgram {
    using System.Runtime.InteropServices;
    using System;

    class Program {
        static void Main(string[] args) {
            ResourceFileUtility.Compiler RFUCompiler = new ResourceFileUtility.Compiler();
            RFUCompiler.info(RFUCompiler.ptr(), "resources.json");

            //ResourceFileUtility.Loader RFULoader = new ResourceFileUtility.Loader();

            //char modelBytes = RFULoader.open("cone");
            // using this method you may be able to "stream" data
            // ResourceFileUtility.Stream songStream = RFULoader.stream("song");
            //songStream.pos(0);
            // get 4 bytes from selector, selector increments by 4
            //char modelBytes4 = songStream.get(4); // first 4 bytes
            //modelBytes4 = songStream.get(4); // next 4 bytes

            // Keep the console window open in debug mode.
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}