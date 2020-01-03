----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/01/2019 04:59:45 PM
-- Design Name: 
-- Module Name: SSD1306_example_TopWrapper - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity SSD1306_example_TopWrapper is
--  Port ( );

  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    scl_0 : inout STD_LOGIC;
    sda_0 : inout STD_LOGIC
  );
end SSD1306_example_TopWrapper;

architecture Behavioral of SSD1306_example_TopWrapper is
component  SSD1306_example_bd_wrapper is
  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    iic_0_scl_io : inout STD_LOGIC;
    iic_0_sda_io : inout STD_LOGIC
  );
end component SSD1306_example_bd_wrapper;

begin
SSD1306_example_TopWrapper: component SSD1306_example_bd_wrapper
 port map (
     DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
     DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
     DDR_cas_n => DDR_cas_n,
     DDR_ck_n => DDR_ck_n,
     DDR_ck_p => DDR_ck_p,
     DDR_cke => DDR_cke,
     DDR_cs_n => DDR_cs_n,
     DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
     DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
     DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
     DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
     DDR_odt => DDR_odt,
     DDR_ras_n => DDR_ras_n,
     DDR_reset_n => DDR_reset_n,
     DDR_we_n => DDR_we_n,
     FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
     FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
     FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
     FIXED_IO_ps_clk => FIXED_IO_ps_clk,
     FIXED_IO_ps_porb => FIXED_IO_ps_porb,
     FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
     iic_0_scl_io => scl_0,
     iic_0_sda_io => sda_0
     );

end Behavioral;
