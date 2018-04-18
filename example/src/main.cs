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
            //RFUCompiler.pack("assets.data");
            RFUCompiler.pack("assets.data", new Callback());

            // Keep the console window open in debug mode.
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}