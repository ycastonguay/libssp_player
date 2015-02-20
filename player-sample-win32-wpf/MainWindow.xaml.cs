using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using org.sessionsapp.player;

namespace player_sample_win32_wpf
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            InitializePlayer();
        }

        private void InitializePlayer()
        {
            int version = SSP.SSP_GetVersion();
            Console.WriteLine("libssp_player version {0}", version);

            int error = SSP.SSP_Init(string.Empty);
            HandleSspError(error);

            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, true);
            HandleSspError(error);
        }

        private void HandleSspError(int sspError)
        {
            if (sspError != SSP.SSP_OK)
            {
                Console.WriteLine("SSP Error {0}", sspError);
            }
        }

    }
}
