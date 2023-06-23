namespace prac_MTUCI
{
    partial class task2
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
            this.components = new System.ComponentModel.Container();
            this.to_statement = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxL1 = new System.Windows.Forms.TextBox();
            this.textBoxL2 = new System.Windows.Forms.TextBox();
            this.textBoxL3 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxS1 = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxS2 = new System.Windows.Forms.TextBox();
            this.textBoxS3 = new System.Windows.Forms.TextBox();
            this.Calculate = new System.Windows.Forms.Button();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // to_statement
            // 
            this.to_statement.Location = new System.Drawing.Point(330, 12);
            this.to_statement.Name = "to_statement";
            this.to_statement.Size = new System.Drawing.Size(101, 41);
            this.to_statement.TabIndex = 3;
            this.to_statement.Text = "К условию";
            this.to_statement.UseVisualStyleBackColor = true;
            this.to_statement.Click += new System.EventHandler(this.to_statement_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(29, 92);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(127, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Значение Аргумента L1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(317, 92);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(127, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Значение Аргумента L2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(607, 92);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(127, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Значение Аргумента L3";
            // 
            // textBoxL1
            // 
            this.textBoxL1.Location = new System.Drawing.Point(32, 109);
            this.textBoxL1.Name = "textBoxL1";
            this.textBoxL1.Size = new System.Drawing.Size(124, 20);
            this.textBoxL1.TabIndex = 7;
            // 
            // textBoxL2
            // 
            this.textBoxL2.Location = new System.Drawing.Point(320, 109);
            this.textBoxL2.Name = "textBoxL2";
            this.textBoxL2.Size = new System.Drawing.Size(124, 20);
            this.textBoxL2.TabIndex = 8;
            // 
            // textBoxL3
            // 
            this.textBoxL3.Location = new System.Drawing.Point(610, 109);
            this.textBoxL3.Name = "textBoxL3";
            this.textBoxL3.Size = new System.Drawing.Size(124, 20);
            this.textBoxL3.TabIndex = 9;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 190);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(133, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Значение Выражения S1";
            // 
            // textBoxS1
            // 
            this.textBoxS1.Location = new System.Drawing.Point(32, 206);
            this.textBoxS1.Name = "textBoxS1";
            this.textBoxS1.Size = new System.Drawing.Size(124, 20);
            this.textBoxS1.TabIndex = 11;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(317, 190);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(133, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "Значение Выражения S2";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(607, 190);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(133, 13);
            this.label6.TabIndex = 13;
            this.label6.Text = "Значение Выражения S3";
            // 
            // textBoxS2
            // 
            this.textBoxS2.Location = new System.Drawing.Point(320, 206);
            this.textBoxS2.Name = "textBoxS2";
            this.textBoxS2.Size = new System.Drawing.Size(124, 20);
            this.textBoxS2.TabIndex = 14;
            // 
            // textBoxS3
            // 
            this.textBoxS3.Location = new System.Drawing.Point(610, 206);
            this.textBoxS3.Name = "textBoxS3";
            this.textBoxS3.Size = new System.Drawing.Size(124, 20);
            this.textBoxS3.TabIndex = 15;
            // 
            // Calculate
            // 
            this.Calculate.Location = new System.Drawing.Point(330, 294);
            this.Calculate.Name = "Calculate";
            this.Calculate.Size = new System.Drawing.Size(101, 41);
            this.Calculate.TabIndex = 16;
            this.Calculate.Text = "Высчитать";
            this.Calculate.UseVisualStyleBackColor = true;
            this.Calculate.Click += new System.EventHandler(this.Calculate_Click);
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // task2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 461);
            this.Controls.Add(this.Calculate);
            this.Controls.Add(this.textBoxS3);
            this.Controls.Add(this.textBoxS2);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxS1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textBoxL3);
            this.Controls.Add(this.textBoxL2);
            this.Controls.Add(this.textBoxL1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.to_statement);
            this.Name = "task2";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Задание №2";
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button to_statement;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxL1;
        private System.Windows.Forms.TextBox textBoxL2;
        private System.Windows.Forms.TextBox textBoxL3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxS1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxS2;
        private System.Windows.Forms.TextBox textBoxS3;
        private System.Windows.Forms.Button Calculate;
        private System.Windows.Forms.ErrorProvider errorProvider1;
    }
}