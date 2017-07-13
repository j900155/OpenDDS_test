using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Collections.Concurrent;

namespace WindowsFormsApplication1
{


    public partial class Form1 : Form
    {
        // Input Queue (執行續訊息交換)
        static ConcurrentQueue<string>[] Input_Topic_Queue = new ConcurrentQueue<string>[4];
        // process list 
        static List<Process> pss = new List<Process>();
        delegate void SetTextCallback(Label Label, string Resultt);

        class T_Topic
        {
            private string _topic;
            private int _id;
            public DataReceivedEventHandler dateRecivedHanlder;

            public T_Topic(string topic, int id)
            {
                _topic = topic;
                _id = id;
            }
            public string topic
            {
                get { return _topic; }
            }

            public int id
            {
                get { return _id; }
            }
        }
        public Form1()
        {
            InitializeComponent();
            Application.ApplicationExit += new EventHandler(this.OnApplicationExit);

        }

        private void OnApplicationExit(object sender, EventArgs e)
        {
            // 離開程式 kill process
            foreach (var p in pss)
            {
                p.Kill();
            }
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            // 初始化Topic queue
            for (int i = 0; i < 4; i++)
            {
                Input_Topic_Queue[i] = new ConcurrentQueue<string>();
            }

            // 設定 Topic
            // Topic porperty 
            // topic : 主題名稱
            // id :  Input Queue Array index 執行續溝通用
            // dateRecivedHanlder:接收 subscirbe 訊息的匿名函式
            T_Topic t1 = new T_Topic("A", 0);
            // 接收 subscirbe 訊息的實作
            t1.dateRecivedHanlder = (sendingProcess, outLine) =>
            {
                if (!String.IsNullOrEmpty(outLine.Data))
                {
                    string data = outLine.Data;
                    int tindex = data.IndexOf("message data");
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        SetText(label7, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                    }
                }
            };

            T_Topic t2 = new T_Topic("B", 1);
            t2.dateRecivedHanlder = (sendingProcess, outLine) =>
            {
                if (!String.IsNullOrEmpty(outLine.Data))
                {
                    string data = outLine.Data;
                    int tindex = data.IndexOf("message data");
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        SetText(label8, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                    }
                }
            };

            T_Topic t3 = new T_Topic("C", 2);
            t3.dateRecivedHanlder = (sendingProcess, outLine) =>
            {
                if (!String.IsNullOrEmpty(outLine.Data))
                {
                    string data = outLine.Data;
                    int tindex = data.IndexOf("message data");
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        SetText(label9, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                    }
                }
            };

            T_Topic t4 = new T_Topic("D", 3);
            t4.dateRecivedHanlder = (sendingProcess, outLine) =>
            {
                if (!String.IsNullOrEmpty(outLine.Data))
                {
                    string data = outLine.Data;
                    int tindex = data.IndexOf("message data");
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        SetText(label10, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                    }
                }
            };

            // 啟動執行續監控push,subscribe
            Thread oThread1 = new Thread(new ParameterizedThreadStart(push));
            // 啟用執行續並提供所需資訊
            oThread1.Start(t1);
            Thread oThread2 = new Thread(new ParameterizedThreadStart(push));
            oThread2.Start(t2);
            Thread oThread3 = new Thread(new ParameterizedThreadStart(push));
            oThread3.Start(t3);
            Thread oThread4 = new Thread(new ParameterizedThreadStart(push));
            oThread4.Start(t4);
            Thread oThread5 = new Thread(new ParameterizedThreadStart(recevie));
            oThread5.Start(t1);
            Thread oThread6 = new Thread(new ParameterizedThreadStart(recevie));
            oThread6.Start(t2);
            Thread oThread7 = new Thread(new ParameterizedThreadStart(recevie));
            oThread7.Start(t3);
            Thread oThread8 = new Thread(new ParameterizedThreadStart(recevie));
            oThread8.Start(t4);
        }


        // 執行subsciber (t_topic 為訂閱的所需資訊)
        private void recevie(object t_topic)
        {
            // subsciber 程式位置
            String subscirberPath = "D:\\OpenDDS\\input_cmd\\Release\\subscriber.exe";
            // 執行 subsciber
            this.RunSub(subscirberPath, "-DCPSConfigfile D:\\OpenDDS\\input_cmd\\rtps.ini", t_topic);
        }

        // 執行publisher (t_topic 為publisher的所需資訊)
        private void push(object t_topic)
        {
            // publihser 程式位置
            String publisherPath = "D:\\OpenDDS\\input_cmd\\Release\\publisher.exe";
            // 執行 publihser
            this.Run(publisherPath, "-DCPSConfigfile D:\\OpenDDS\\input_cmd\\rtps.ini", t_topic);
        }

        public void Run(string fileName, string args, object top)
        {
            T_Topic tt = (T_Topic)top;
            string returnvalue = string.Empty;
            // 定義呼叫程式的info
            ProcessStartInfo info = new ProcessStartInfo(fileName);
            info.UseShellExecute = false;
            // 設定命令列輸入參數
            info.Arguments = args;
            // 重新導向標準輸出 輸入 錯誤
            info.RedirectStandardInput = true;
            info.RedirectStandardOutput = true;
            info.RedirectStandardError = true;
            // 設定是否建立視窗
            info.CreateNoWindow = true;
            Process process = new Process();
            process.StartInfo = info;
            // 設定標準輸出 , 錯誤的接收事件
            process.OutputDataReceived += new DataReceivedEventHandler(Display);
            process.ErrorDataReceived += new DataReceivedEventHandler(Display);
            // 開始執行程序
            process.Start();
            // 加入process list 用來離開程式 關閉publisher process
            pss.Add(process);
            // 開始讀取標準輸出 , 錯誤
            process.BeginOutputReadLine();
            process.BeginErrorReadLine();
            StreamWriter sw = process.StandardInput;
            // 輸入要傳送的TOPIC
            sw.WriteLine(tt.topic);
            sw.Flush();
            String input;
            while (true)
            {
                // 確任是否在queue中有無要傳送的訊息
                if (Input_Topic_Queue[tt.id] != null && Input_Topic_Queue[tt.id].TryDequeue(out input))
                {
                    // 傳送訊息
                    sw.WriteLine(input);
                    sw.Flush();
                }
                Thread.Sleep(5);
            }
            // 等待程式執行結束
            process.WaitForExit();
        }

        public void RunSub(string fileName, string args, object top)
        {
            T_Topic tt = (T_Topic)top;
            string returnvalue = string.Empty;
            // 定義呼叫程式的info
            ProcessStartInfo info = new ProcessStartInfo(fileName);
            info.UseShellExecute = false;
            // 設定命令列輸入參數
            info.Arguments = args;
            // 設定標準輸出 , 錯誤的接收事件
            info.RedirectStandardInput = true;
            info.RedirectStandardOutput = true;
            info.RedirectStandardError = true;
            // 設定是否建立視窗
            info.CreateNoWindow = true;
            Process process = new Process();
            process.StartInfo = info;
            // 設定標準輸出 , 錯誤的接收事件
            process.OutputDataReceived += new DataReceivedEventHandler(tt.dateRecivedHanlder);
            process.ErrorDataReceived += new DataReceivedEventHandler(Display);
            // 開始執行程序
            process.Start();
            // 加入process list 用來離開程式 關閉subsciber process
            pss.Add(process);
            StreamWriter sw = process.StandardInput;
            // 開始讀取標準輸出 , 錯誤
            process.BeginOutputReadLine();
            process.BeginErrorReadLine();
            // 輸入要訂閱的主題
            sw.WriteLine(tt.topic);
            sw.Flush();
            // 等待程式離開
            process.WaitForExit();
        }


        // 顯示
        void Display(object sendingProcess,
            DataReceivedEventArgs outLine)
        {
            if (!String.IsNullOrEmpty(outLine.Data))
            {
                string data = outLine.Data;
                System.Diagnostics.Debug.WriteLine(outLine.Data);
            }
        }

        // 傳送訊息事件
        private void button1_Click(object sender, EventArgs e)
        {
            // 判斷是否傳送訊息
            if (checkBox1.Checked == true)
            {
                Input_Topic_Queue[0].Enqueue(this.textBox1.Text);
            }
            if (checkBox2.Checked == true)
            {
                Input_Topic_Queue[1].Enqueue(this.textBox3.Text);
            }
            if (checkBox3.Checked == true)
            {
                Input_Topic_Queue[2].Enqueue(this.textBox2.Text);
            }
            if (checkBox4.Checked == true)
            {
                Input_Topic_Queue[3].Enqueue(this.textBox4.Text);
            }
        }

        // 跨執行續修改 UI label 用 (直接在thread修該ui會錯誤)
        private void SetText(Label Label,string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (Label.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { Label, text });
            }
            else
            {
                Label.Text = text;
            }
        }
    }
}
