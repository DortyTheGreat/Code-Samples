namespace prac_MTUCI
{
    partial class task3_statement
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(task3_statement));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.to_task = new System.Windows.Forms.Button();
            this.to_main = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.ImageLocation = "";
            this.pictureBox1.Location = new System.Drawing.Point(12, 168);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(760, 135);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 10;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(266, 152);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(239, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Создать программу для выполнения задания";
            // 
            // to_task
            // 
            this.to_task.Location = new System.Drawing.Point(330, 402);
            this.to_task.Name = "to_task";
            this.to_task.Size = new System.Drawing.Size(101, 41);
            this.to_task.TabIndex = 8;
            this.to_task.Text = "К Заданию";
            this.to_task.UseVisualStyleBackColor = true;
            this.to_task.Click += new System.EventHandler(this.to_task_Click);
            // 
            // to_main
            // 
            this.to_main.Location = new System.Drawing.Point(330, 17);
            this.to_main.Name = "to_main";
            this.to_main.Size = new System.Drawing.Size(101, 41);
            this.to_main.TabIndex = 7;
            this.to_main.Text = "На Главную";
            this.to_main.UseVisualStyleBackColor = true;
            this.to_main.Click += new System.EventHandler(this.to_main_Click);
            // 
            // task3_statement
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 461);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.to_task);
            this.Controls.Add(this.to_main);
            this.Name = "task3_statement";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Условие Третьего Задания";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button to_task;
        private System.Windows.Forms.Button to_main;
    }
}