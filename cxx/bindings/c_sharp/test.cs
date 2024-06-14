using System;
using Cinnamon;

class Program
{
    static void Main(string[] args)
    {
        Environment env = new Environment();
        ServiceManager serviceManager = new ServiceManager(env.GetEnv());

        string modelPath = "../models/test_wb.onnx";
        serviceManager.CreateModel(modelPath);

        serviceManager.UpdateSessionClock(modelPath);

        float duration = serviceManager.GetSessionClock(modelPath);
        Console.WriteLine($"Initial session duration: {duration} seconds");

        System.Threading.Thread.Sleep(2000);

        duration = serviceManager.GetSessionClock(modelPath);
        Console.WriteLine($"Session duration after 2 seconds: {duration} seconds");
    }
}