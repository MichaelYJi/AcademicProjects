using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZooManager;

namespace ZooManager
{
    public partial class Form1 : Form
    {
        // opens builder and binding source
        private SqlConnectionStringBuilder builder;
        private SqlDataAdapter dataAdapter = new SqlDataAdapter();
        private BindingSource bSource = new BindingSource();

        public Form1()
        {
            InitializeComponent();

            try
            {
                //credentials
                builder = new SqlConnectionStringBuilder();
                builder.DataSource = "zoomangroup.database.windows.net";
                builder.UserID = "ZooMan_Admin";
                builder.Password = "ParsonsWinter2018!";
                builder.InitialCatalog = "ZooManager";

            }
            catch (SqlException e)
            {
                MessageBox.Show(e.ToString());
            }

            // binds the data grid's source
            dataGrid.DataSource = bSource;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            // clear the grid
            dataGrid.ClearSelection();
            // if nothing in grid dont do anything
            if (textBox1.TextLength == 0)
            {
                return;
            }
            // attempt query
            using (SqlConnection connection = new SqlConnection(builder.ConnectionString))
            {
                connection.Open();
                String query = "select animal.givenName, animal.commonName from exhibit,hub,animal where hid = id and eno = '" + textBox1.Text + "' and eno = number";

                GetData(query);

                connection.Close();
            }


        }

        private void dataGrid_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        // function that gets the data
        public void GetData(string selectCommand)
        {
            try
            {
                // create a data adapter
                SqlConnection connection = new SqlConnection(builder.ConnectionString);
                dataAdapter = new SqlDataAdapter(selectCommand, connection);

                // makes a sql query
                SqlCommandBuilder commandBuilder = new SqlCommandBuilder(dataAdapter);

                // add the data into as a table
                DataTable table = new DataTable();
                table.Locale = System.Globalization.CultureInfo.InvariantCulture;
                dataAdapter.Fill(table);
                bSource.DataSource = table;
            }
            catch (SqlException e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            dataGrid.ClearSelection();

            using (SqlConnection connection = new SqlConnection(builder.ConnectionString))
            {
                connection.Open();
                String query = "Select count(*) as Total_Animals, HUB.id from ANIMAL, HUB where ANIMAL.eno in (select EXHIBIT.number from EXHIBIT where HUB.id = EXHIBIT.hid) group by HUB.id";

                GetData(query);

                connection.Close();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            dataGrid.ClearSelection();
            if (textBox2.TextLength == 0)
            {
                return;
            }
            using (SqlConnection connection = new SqlConnection(builder.ConnectionString))
            {
                connection.Open();
                String query = "Select * from ANIMAL where commonName = '" + textBox2.Text + "'";

                GetData(query);

                connection.Close();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            dataGrid.ClearSelection();

            using (SqlConnection connection = new SqlConnection(builder.ConnectionString))
            {
                connection.Open();
                String query = "Select count(*), ANIMAL.commonName from ANIMAL group by ANIMAL.commonName;";

                GetData(query);

                connection.Close();
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            dataGrid.ClearSelection();
            if (textBox3.TextLength == 0)
            {
                return;
            }
            using (SqlConnection connection = new SqlConnection(builder.ConnectionString))
            {
                connection.Open();
                String query = "Select * from ANIMAL, HUB where HUB.id = '" + textBox3.Text + "' AND ANIMAL.eno IN (Select EXHIBIT.number from EXHIBIT where HUB.id = EXHIBIT.hid AND HUB.id = '" + textBox3.Text + "')";

                GetData(query);

                connection.Close();
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.Show();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            dataGrid.ClearSelection();

            using (SqlConnection connection = new SqlConnection(builder.ConnectionString))
            {
                connection.Open();
                String query = "Select distinct commonName from Animal";

                GetData(query);

                connection.Close();
            }
        }
    }
}
