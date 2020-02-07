using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace KeChengBiao
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        [DllImport("Kernel32.dll")]
        public static extern bool Beep(int frequency, int duration);

        private int LessonCount;
        private void Form1_Load(object sender, EventArgs e)
        {
            this.MaximizeBox = false;
            //this.MinimizeBox = false;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;

            int index = 0;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "8:00-8:30";
            dataGridView1.Rows[index].Cells[0].Value = "早读";
            dataGridView1.Rows[index].Cells[1].Value = "早读";
            dataGridView1.Rows[index].Cells[2].Value = "早读";
            dataGridView1.Rows[index].Cells[3].Value = "早读";
            dataGridView1.Rows[index].Cells[4].Value = "早读";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "8:40-9:20";
            dataGridView1.Rows[index].Cells[0].Value = "英语";
            dataGridView1.Rows[index].Cells[1].Value = "英语";
            dataGridView1.Rows[index].Cells[2].Value = "英语";
            dataGridView1.Rows[index].Cells[3].Value = "英语";
            dataGridView1.Rows[index].Cells[4].Value = "英语";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "9:30-10:10";
            dataGridView1.Rows[index].Cells[0].Value = "英语";
            dataGridView1.Rows[index].Cells[1].Value = "英语";
            dataGridView1.Rows[index].Cells[2].Value = "英语";
            dataGridView1.Rows[index].Cells[3].Value = "英语";
            dataGridView1.Rows[index].Cells[4].Value = "英语";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "10:20-11:00";
            dataGridView1.Rows[index].Cells[0].Value = "数学";
            dataGridView1.Rows[index].Cells[1].Value = "数学";
            dataGridView1.Rows[index].Cells[2].Value = "数学";
            dataGridView1.Rows[index].Cells[3].Value = "数学";
            dataGridView1.Rows[index].Cells[4].Value = "数学";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "11:10-11:40";
            dataGridView1.Rows[index].Cells[0].Value = "数学";
            dataGridView1.Rows[index].Cells[1].Value = "数学";
            dataGridView1.Rows[index].Cells[2].Value = "数学";
            dataGridView1.Rows[index].Cells[3].Value = "数学";
            dataGridView1.Rows[index].Cells[4].Value = "数学";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "午休";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "13:20-14:00";
            dataGridView1.Rows[index].Cells[0].Value = "语文";
            dataGridView1.Rows[index].Cells[1].Value = "语文";
            dataGridView1.Rows[index].Cells[2].Value = "语文";
            dataGridView1.Rows[index].Cells[3].Value = "语文";
            dataGridView1.Rows[index].Cells[4].Value = "语文";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "14:10-14:50";
            dataGridView1.Rows[index].Cells[0].Value = "阅读";
            dataGridView1.Rows[index].Cells[1].Value = "阅读";
            dataGridView1.Rows[index].Cells[2].Value = "阅读";
            dataGridView1.Rows[index].Cells[3].Value = "阅读";
            dataGridView1.Rows[index].Cells[4].Value = "阅读";

            index++;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[index].HeaderCell.Value = "15:00-15:50";
            dataGridView1.Rows[index].Cells[0].Value = "自习";
            dataGridView1.Rows[index].Cells[1].Value = "自习";
            dataGridView1.Rows[index].Cells[2].Value = "自习";
            dataGridView1.Rows[index].Cells[3].Value = "自习";
            dataGridView1.Rows[index].Cells[4].Value = "自习";

            LessonCount = index;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            string week = GetWeek();
            int i = 0;

            for(i=0; i< dataGridView1.ColumnCount; i++)
            {
                //MessageBox.Show(dataGridView1.Columns[index].HeaderText);
                if(week == dataGridView1.Columns[i].HeaderText)
                {
                    int lession = GetLession();
                    if(lession >=0 && lession <= LessonCount)
                    {
                        dataGridView1.CurrentCell = dataGridView1[i, lession];
                    }
                    else
                    {
                        dataGridView1.CurrentCell = dataGridView1[i, 5];
                    }
                }
            }
        }

        private int GetLession()
        {
            DateTime dt = DateTime.Now;
            int hour = dt.Hour;
            int minute = dt.Minute;
            //MessageBox.Show(hour.ToString());
            int index = 0;

            if(hour == 8 && minute >= 0 && minute <= 30)
            {
                return index;
            }

            index++;
            if ((hour == 8 && minute >= 40 && minute <= 59) || (hour == 9 && minute >= 0 && minute <= 20))
            {
                return index;
            }

            index++;
            if ((hour == 9 && minute >= 30 && minute <= 59) || (hour == 10 && minute >= 0 && minute <= 10))
            {
                return index;
            }

            index++;
            if (hour == 10 && minute >= 20 && minute <= 59)
            {
                return index;
            }

            index++;
            if (hour == 11 && minute >= 10 && minute <= 40)
            {
                return index;
            }

            index++;
            if (hour == 11 && minute >= 10 && minute <= 40)
            {
                return index;
            }

            index++;
            if (hour == 13 && minute >= 20 && minute <= 59)
            {
                return index;
            }

            index++;
            if (hour == 14 && minute >= 10 && minute <= 50)
            {
                return index;
            }

            index++;
            if (hour == 15 && minute >= 0 && minute <= 50)
            {
                return index;
            }

            return -1;
        }
        private string GetWeek()
        {
            string week = string.Empty;
            switch ((int)DateTime.Now.DayOfWeek)
            {
                case 0:
                    week = "星期日";
                    break;
                case 1:
                    week = "星期一";
                    break;
                case 2:
                    week = "星期二";
                    break;
                case 3:
                    week = "星期三";
                    break;
                case 4:
                    week = "星期四";
                    break;
                case 5:
                    week = "星期五";
                    break;
                default:
                    week = "星期六";
                    break;
            }
            return week;
        }

        private void ClassBegin()
        {
            Beep(2000, 5000);
            System.Threading.Thread.Sleep(60 * 1000);
        }

        private void ClassOver()
        {
            Beep(1000, 5000);
            System.Threading.Thread.Sleep(60*1000);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            DateTime dt = DateTime.Now;
            int hour = dt.Hour;
            int minute = dt.Minute;

            //上课
            if (hour == 8 && minute == 0)
            {
                ClassBegin();
            }

            if (hour == 8 && minute == 40)
            {
                ClassBegin();
            }

            if (hour == 9 && minute == 30)
            {
                ClassBegin();
            }

            if (hour == 10 && minute == 20)
            {
                ClassBegin();
            }

            if (hour == 10 && minute == 20)
            {
                ClassBegin();
            }

            if (hour == 11 && minute == 10)
            {
                ClassBegin();
            }

            if (hour == 13 && minute == 20)
            {
                ClassBegin();
            }

            if (hour == 14 && minute == 10)
            {
                ClassBegin();
            }

            if (hour == 15 && minute == 0)
            {
                ClassBegin();
            }

            //下课
            if (hour == 8 && minute == 30)
            {
                ClassOver();
            }
            if (hour == 9 && minute == 20)
            {
                ClassOver();
            }
            if (hour == 10 && minute == 10)
            {
                ClassOver();
            }
            if (hour == 11 && minute == 40)
            {
                ClassOver();
            }
            if (hour == 14 && minute == 00)
            {
                ClassOver();
            }
            if (hour == 14 && minute == 50)
            {
                ClassOver();
            }
            if (hour == 15 && minute == 00)
            {
                ClassOver();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Beep(2000, 5000);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Beep(1000, 5000);
        }
    }
}
