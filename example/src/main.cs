namespace ExampleProgram {
    using System.Runtime.InteropServices;
    using System;

    class Callback : ResourceFileUtility.CallbackHandler {
        public override void fileComplete(string filePath) {
            Console.WriteLine("Sucessfully Packed: " + filePath);
        }
        public override void packComplete() {
            Console.WriteLine("Sucessfully Packed all files!");
        }
    }

    class Program {
        static void Main(string[] args) {
            ResourceFileUtility.Compiler RFUCompiler = new ResourceFileUtility.Compiler();
            RFUCompiler.info("resources.json");
            RFUCompiler.pack("assets.data");
            RFUCompiler.pack("assets.data", new Callback());

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