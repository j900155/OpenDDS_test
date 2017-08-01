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
        static ConcurrentQueue<T_Data>[] Input_Topic_Queue = new ConcurrentQueue<T_Data>[4];
        // process list 
        static List<Process> pss = new List<Process>();
        delegate void SetTextCallback(Label Label, string Resultt);
        static long[] counts = {0,0,0,0 };

        struct T_Data
        {
            public string data;
            public long count;
        }
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
                Input_Topic_Queue[i] = new ConcurrentQueue<T_Data>();
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
                    string cstr = "message count ";
                    string estr = ";message time ";
                    int tindex = data.IndexOf(cstr);
                    int eindex = data.IndexOf(estr);
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        int len = eindex - (tindex + cstr.Length);
                        long count = Convert.ToInt64(data.Substring(tindex + cstr.Length, len));
                        SetText(label7, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                        T_Data da = new T_Data();
                        da.data = this.textBox1.Text;
                        if (checkBox5.Checked == true)
                        {
                            if (count != -1 && count >= Convert.ToInt64(textBox6.Text) && Convert.ToInt64(textBox6.Text) != 0)
                            {
                                counts[0] = -1;
                                return;
                            }
                            if (timer1_count == Convert.ToInt64(textBox5.Text) && Convert.ToInt64(textBox5.Text) != 0)
                            {
                                counts[0] = -1;
                                return;
                            }

                            if (count == counts[0] + 1)
                            {
                                counts[0] = counts[0] + 2;
                                da.count = counts[0];
                                Input_Topic_Queue[0].Enqueue(da);
                            }
                        }
                    }
                }
            };

            T_Topic t2 = new T_Topic("B", 1);
            t2.dateRecivedHanlder = (sendingProcess, outLine) =>
            {
                if (!String.IsNullOrEmpty(outLine.Data))
                {
                    string data = outLine.Data;
                    string cstr = "message count ";
                    string estr = ";message time ";
                    int tindex = data.IndexOf(cstr);
                    int eindex = data.IndexOf(estr);
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        SetText(label8, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                        int len = eindex - (tindex + cstr.Length);
                        long count = Convert.ToInt64(data.Substring(tindex + cstr.Length, len));
                        T_Data da = new T_Data();
                        da.data = this.textBox3.Text;
                        if (checkBox5.Checked == true)
                        {
                            if (count != -1 && count >= Convert.ToInt64(textBox8.Text) && Convert.ToInt64(textBox8.Text) != 0)
                            {
                                counts[1] = -1;
                                return;
                            }
                            if (timer2_count == Convert.ToInt64(textBox7.Text) && Convert.ToInt64(textBox7.Text) != 0)
                            {
                                counts[1] = -1;
                                return;
                            }
                            if (count == counts[1] + 1)
                            {
                                counts[1] = counts[1] + 2;
                                da.count = counts[1];
                                Input_Topic_Queue[1].Enqueue(da);
                            }
                        }
                    }
                }
            };

            T_Topic t3 = new T_Topic("C", 2);
            t3.dateRecivedHanlder = (sendingProcess, outLine) =>
            {
                if (!String.IsNullOrEmpty(outLine.Data))
                {
                    string data = outLine.Data;
                    string cstr = "message count ";
                    string estr = ";message time ";
                    int tindex = data.IndexOf(cstr);
                    int eindex = data.IndexOf(estr);
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        SetText(label9, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                        int len = eindex - (tindex + cstr.Length);
                        long count = Convert.ToInt64(data.Substring(tindex + cstr.Length, len));
                        T_Data da = new T_Data();
                        da.data = this.textBox2.Text;
                        if (checkBox5.Checked == true)
                        {
                            if (count != -1 && count >= Convert.ToInt64(textBox10.Text) && Convert.ToInt64(textBox10.Text) != 0)
                            {
                                counts[2] = -1;
                                return;
                            }
                            if (timer3_count == Convert.ToInt64(textBox9.Text) && Convert.ToInt64(textBox9.Text) != 0)
                            {
                                counts[2] = -1;
                                return;
                            }
                            if (count == counts[2] + 1)
                            {
                                counts[2] = counts[2] + 2;
                                da.count = counts[2];
                                Input_Topic_Queue[2].Enqueue(da);
                            }
                        }
                    }
                }
            };

            T_Topic t4 = new T_Topic("D", 3);
            t4.dateRecivedHanlder = (sendingProcess, outLine) =>
            {
                if (!String.IsNullOrEmpty(outLine.Data))
                {
                    string data = outLine.Data;
                    string cstr = "message count ";
                    string estr = ";message time ";
                    int tindex = data.IndexOf(cstr);
                    int eindex = data.IndexOf(estr);
                    System.Diagnostics.Debug.WriteLine(outLine.Data);
                    if (tindex >= 0)
                    {
                        SetText(label10, outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                        System.Diagnostics.Debug.WriteLine(outLine.Data);
                        int len = eindex - (tindex + cstr.Length);
                        long count = Convert.ToInt64(data.Substring(tindex + cstr.Length, len));
                        T_Data da = new T_Data();
                        da.data = this.textBox4.Text;
                        if (checkBox5.Checked == true)
                        {
                            if (count != -1 && count >= Convert.ToInt64(textBox12.Text) && Convert.ToInt64(textBox12.Text) != 0)
                            {
                                counts[3] = -1;
                                return;
                            }
                            if (timer4_count == Convert.ToInt64(textBox11.Text) && Convert.ToInt64(textBox11.Text) != 0)
                            {
                                counts[3] = -1;
                                return;
                            }
                            if (count == counts[3] + 1)
                            {
                                counts[3] = counts[3] + 2;
                                da.count = counts[3];
                                Input_Topic_Queue[3].Enqueue(da);
                            }
                        }
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
            String subscirberPath = "D:\\OpenDDS\\OpenDDS_test-master\\input_cmd\\Release\\subscriber.exe";
            // 執行 subsciber
            this.RunSub(subscirberPath, "-DCPSConfigfile D:\\OpenDDS\\OpenDDS_test-master\\input_cmd\\rtps.ini", t_topic);
        }

        // 執行publisher (t_topic 為publisher的所需資訊)
        private void push(object t_topic)
        {
            // publihser 程式位置
            String publisherPath = "D:\\OpenDDS\\OpenDDS_test-master\\input_cmd\\Release\\publisher.exe";
            // 執行 publihser
            this.Run(publisherPath, "-DCPSConfigfile D:\\OpenDDS\\OpenDDS_test-master\\input_cmd\\rtps.ini", t_topic);
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
            T_Data input;
            while (true)
            {
                // 確任是否在queue中有無要傳送的訊息
                if (Input_Topic_Queue[tt.id] != null && Input_Topic_Queue[tt.id].TryDequeue(out input))
                {
                    // 傳送訊息
                    sw.WriteLine(input.data);
                    sw.Flush();
                    // 傳送訊息
                    sw.WriteLine(input.count);
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
            for (int i = 0; i < 4; i++)
            {
                counts[i] = 0;
            }
            if (checkBox1.Checked == true)
            {
                T_Data data = new T_Data();
                data.data = this.textBox1.Text;
                data.count = 0;
                Input_Topic_Queue[0].Enqueue(data);
            }
            if (checkBox2.Checked == true)
            {
                T_Data data = new T_Data();
                data.data = this.textBox3.Text;
                data.count = 0;
                Input_Topic_Queue[1].Enqueue(data);
            }
            if (checkBox3.Checked == true)
            {
                T_Data data = new T_Data();
                data.data = this.textBox2.Text;
                data.count = 0;
                Input_Topic_Queue[2].Enqueue(data);
            }
            if (checkBox4.Checked == true)
            {
                T_Data data = new T_Data();
                data.data = this.textBox4.Text;
                data.count = 0;
                Input_Topic_Queue[3].Enqueue(data);
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


        long timer1_count, timer2_count, timer3_count, timer4_count;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (counts[0] == -1)
            {
                timer1.Stop();
                button2.Text = "開始";
            }
            if (checkBox5.Checked == true)
            {
                timer1_count++;
            }
            else
            {
                T_Data data = new T_Data();
                data.data = this.textBox1.Text;
                data.count = counts[0]++;
                Input_Topic_Queue[0].Enqueue(data);
            }

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (counts[1] == -1)
            {
                timer2.Stop();
                button3.Text = "開始";
            }
            if (checkBox5.Checked == true)
            {
                timer2_count++;
            }
            else
            {
                T_Data data = new T_Data();
                data.data = this.textBox3.Text;
                data.count = counts[1]++;
                Input_Topic_Queue[1].Enqueue(data);
            }
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            if (counts[2] == -1)
            {
                timer3.Stop();
                button4.Text = "開始";
            }
            if (checkBox5.Checked == true)
            {
                timer3_count++;
            }
            else
            {
                T_Data data = new T_Data();
                data.data = this.textBox2.Text;
                data.count = counts[2]++;
                Input_Topic_Queue[2].Enqueue(data);
            }
        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            if (counts[3] == -1)
            {
                timer4.Stop();
                button5.Text = "開始";
            }
            if (checkBox5.Checked == true)
            {
                timer4_count++;
            }
            else
            {
                T_Data data = new T_Data();
                data.data = this.textBox4.Text;
                data.count = counts[3]++;
                Input_Topic_Queue[3].Enqueue(data);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!this.timer1.Enabled)
            {
                counts[0] = 0;
                if (checkBox5.Checked == true)
                {
                    T_Data data = new T_Data();
                    data.data = this.textBox1.Text;
                    data.count = ++counts[0];
                    Input_Topic_Queue[0].Enqueue(data);
                    timer1_count = 0;
                    this.timer1.Interval = 1000;
                }
                else
                {
                    this.timer1.Interval = Convert.ToInt32(textBox5.Text);
                }
                this.timer1.Start();
                ((Button)sender).Text = "停止";
            }
            else
            {
                this.timer1.Stop();
                ((Button)sender).Text = "開始";
            }

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (!this.timer2.Enabled)
            {
                counts[1] = 0;
                if (checkBox5.Checked == true)
                {
                    T_Data data = new T_Data();
                    data.data = this.textBox3.Text;
                    data.count = ++counts[1];
                    Input_Topic_Queue[1].Enqueue(data);
                    timer2_count = 0;
                    this.timer2.Interval = 1000;
                }
                else
                {
                    this.timer2.Interval = Convert.ToInt32(textBox7.Text);
                }
                this.timer2.Start();
                ((Button)sender).Text = "停止";
            }
            else
            {
                this.timer2.Stop();
                ((Button)sender).Text = "開始";
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (!this.timer3.Enabled)
            {
                counts[2] = 0;
                if (checkBox5.Checked == true)
                {
                    T_Data data = new T_Data();
                    data.data = this.textBox2.Text;
                    data.count = ++counts[2];
                    Input_Topic_Queue[2].Enqueue(data);
                    timer3_count = 0;
                    this.timer3.Interval = 1000;
                }
                else
                {
                    this.timer3.Interval = Convert.ToInt32(textBox9.Text);
                }
                this.timer3.Start();
                ((Button)sender).Text = "停止";
            }
            else
            {
                this.timer3.Stop();
                ((Button)sender).Text = "開始";
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (!this.timer4.Enabled)
            {
                counts[3] = 0;
                if (checkBox5.Checked == true)
                {
                    T_Data data = new T_Data();
                    data.data = this.textBox4.Text;
                    data.count = ++counts[3];
                    Input_Topic_Queue[3].Enqueue(data);
                    timer4_count = 0;
                    this.timer4.Interval = 1000;
                }
                else
                {
                    this.timer4.Interval = Convert.ToInt32(textBox11.Text);
                }
                this.timer4.Start();
                ((Button)sender).Text = "停止";
            }
            else
            {
                this.timer4.Stop();
                ((Button)sender).Text = "開始";
            }
        }

        private void num_TextChange(object sender, KeyPressEventArgs e)
        {
            if (((int)e.KeyChar < 48 | (int)e.KeyChar > 57) & (int)e.KeyChar != 8)
            {
                e.Handled = true;
            }
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
