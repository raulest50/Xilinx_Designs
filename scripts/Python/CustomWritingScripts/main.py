import numpy as np
import matplotlib.pyplot as plt

from fxpmath import Fxp

entity_name = "stream_source"
file_name = f"{entity_name}.vhd"
signal_points = 8192
data_bit_size = 13  # axis_tdata bus width

file = open(file_name, "w")

t = np.linspace(0, 2*np.pi, signal_points)
signal = 2*(np.sin(t) + np.sin(t*2))

plt.plot(signal)
plt.show()

data = ""

for k in range(0, signal_points):
    if k == signal_points-1:  # ultimo ciclo
        data += f" {k} => b\"{Fxp(signal[k], signed=True, n_word=data_bit_size, n_frac=8).bin()}\" \n"
    else:
        if (k+1) % 4 == 0 and k > 0:
            data += f" {k} => b\"{Fxp(signal[k], signed=True, n_word=data_bit_size, n_frac=8).bin() }\",\n"
        else:
            data += f" {k} => b\"{Fxp(signal[k], signed=True, n_word=data_bit_size, n_frac=8).bin() }\", "


body = f"""

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity {entity_name} is
    Port (
    clk : in std_logic;
    nrst : in std_logic;
    axis_mtr_tready : in std_logic;
    axis_mtr_tvalid : out std_logic;
    axis_mtr_tdata : out std_logic_vector({data_bit_size-1} downto 0)
    );
end {entity_name};

architecture Behavioral of {entity_name} is

type estado is (init, tvalid, tready);
signal n : integer range 0 to {signal_points-1} := 0;

type data_8x32 is array (0 to {signal_points-1}) of std_logic_vector({data_bit_size-1} downto 0);

constant my_data : data_8x32  :=
(
    {data}
);

signal state, nx_state : estado;

signal data_valid : std_logic;

begin

    update_state : process(clk, nrst)
    begin
        if rising_edge(clk) then
            if nrst = '0' then
                state <= init;
            else
                state <= nx_state;
            end if;
        end if;
    end process update_state;


    next_state : process(state)
    begin
        case state is
        when init =>
            n <= 0;
            axis_mtr_tdata <= my_data(n);
            axis_mtr_tvalid <= '0';
            nx_state <= tvalid;
        when tvalid =>
            axis_mtr_tdata <= my_data(n);
            axis_mtr_tvalid <= '1';
            if axis_mtr_tready = '1' then
                nx_state <= tready;
            end if;
        when tready =>
            n <= n+1;
            if n={signal_points-1} then n <= 0; end if; -- counter reset at {signal_points-1}
            axis_mtr_tvalid <= '0';
            nx_state <= tvalid;
        when others =>
            n <= 0;
            axis_mtr_tvalid <= '0';
            axis_mtr_tdata <= my_data(n);
            nx_state <= init;
        end case;
    end process next_state;

end Behavioral;

"""

file.write(body)
file.close()

