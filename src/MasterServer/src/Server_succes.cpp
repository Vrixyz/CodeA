#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

void	Server::checkSucces(User *u)
{
  if (u->succes[0] != '1')
    checkSucces_1(u);
  if (u->succes[1] != '1')
    checkSucces_2(u);
  if (u->succes[2] != '1')
    checkSucces_3(u);
  if (u->succes[3] != '1')
    checkSucces_4(u);
  if (u->succes[4] != '1')
    checkSucces_5(u);
  if (u->succes[5] != '1')
    checkSucces_6(u);
  if (u->succes[6] != '1')
    checkSucces_7(u);
  if (u->succes[7] != '1')
    checkSucces_8(u);
  if (u->succes[8] != '1')
    checkSucces_9(u);
  if (u->succes[9] != '1')
    checkSucces_10(u);
  if (u->succes[10] != '1')
    checkSucces_11(u);
  if (u->succes[11] != '1')
    checkSucces_12(u);
  if (u->succes[12] != '1')
    checkSucces_13(u);
  if (u->succes[13] != '1')
    checkSucces_14(u);
  if (u->succes[14] != '1')
    checkSucces_15(u);
  if (u->succes[15] != '1')
    checkSucces_16(u);
  if (u->succes[16] != '1')
    checkSucces_17(u);
  if (u->succes[17] != '1')
    checkSucces_18(u);
  if (u->succes[18] != '1')
    checkSucces_19(u);
  if (u->succes[19] != '1')
    checkSucces_20(u);
  if (u->succes[20] != '1')
    checkSucces_21(u);
  if (u->succes[21] != '1')
    checkSucces_22(u);
  if (u->succes[22] != '1')
    checkSucces_23(u);
  if (u->succes[23] != '1')
    checkSucces_24(u);
  if (u->succes[24] != '1')
    checkSucces_25(u);
  if (u->succes[25] != '1')
    checkSucces_26(u);
  if (u->succes[26] != '1')
    checkSucces_27(u);
  if (u->succes[27] != '1')
    checkSucces_28(u);
  if (u->succes[28] != '1')
    checkSucces_29(u);
  if (u->succes[29] != '1')
    checkSucces_30(u);
  if (u->succes[30] != '1')
    checkSucces_31(u);
  if (u->succes[31] != '1')
    checkSucces_32(u);
  if (u->succes[32] != '1')
    checkSucces_33(u);
  if (u->succes[33] != '1')
    checkSucces_34(u);
  if (u->succes[34] != '1')
    checkSucces_35(u);
  if (u->succes[35] != '1')
    checkSucces_36(u);
  if (u->succes[36] != '1')
    checkSucces_37(u);
  if (u->succes[37] != '1')
    checkSucces_38(u);
  if (u->succes[38] != '1')
    checkSucces_39(u);
  if (u->succes[39] != '1')
    checkSucces_40(u);
  if (u->succes[40] != '1')
    checkSucces_41(u);
  if (u->succes[41] != '1')
    checkSucces_42(u);
  if (u->succes[42] != '1')
    checkSucces_43(u);
  if (u->succes[43] != '1')
    checkSucces_44(u);
  if (u->succes[44] != '1')
    checkSucces_45(u);
}

void	Server::checkSucces_1(User *u)
{
  /* SALADE DE PHALANGES */
  if (u->games_win_1 >= 1)
    u->succes[0] = '1';
}

void	Server::checkSucces_2(User *u)
{
  /* VITE LE DPR ARRIVE */
  if (u->games_win_1 >= 1)
    u->succes[1] = '1';
}

void	Server::checkSucces_3(User *u)
{
  /* HMM... GAGNE D'AVANCE */
  if (u->games_win_1 >= 1)
    u->succes[2] = '1';
}

void	Server::checkSucces_4(User *u)
{
  /* SHIELDS ! SHIELDS EVERYWHERE */
  if (u->games_win_1 >= 1)
    u->succes[3] = '1';
}

void	Server::checkSucces_5(User *u)
{
  /* LES RENFORS SONT LA */
  if (u->games_win_1 >= 1)
    u->succes[4] = '1';
}

void	Server::checkSucces_6(User *u)
{
  /* MAGE 1 1 */
  if (u->games_played_1 >= 1)
    u->succes[5] = '1';
}

void	Server::checkSucces_7(User *u)
{
  /* MAGE 1 2 */
  if (u->games_played_1 >= 25)
    u->succes[6] = '1';
}

void	Server::checkSucces_8(User *u)
{
  /* MAGE 1 3 */
  if (u->games_played_1 >= 100)
    u->succes[7] = '1';
}

void	Server::checkSucces_9(User *u)
{
  /* MAGE 1 4 */
  if (u->games_played_1 >= 250)
    u->succes[8] = '1';
}

void	Server::checkSucces_10(User *u)
{
  /* MAGE 1 5 */
  if (u->games_played_1 >= 1000)
    u->succes[9] = '1';
}

void	Server::checkSucces_11(User *u)
{
  /* MAGE 2 1 */
  if (u->games_win_1 >= 1)
    u->succes[10] = '1';
}

void	Server::checkSucces_12(User *u)
{
  /* MAGE 2 2 */
  if (u->games_win_1 >= 25)
    u->succes[11] = '1';
}

void	Server::checkSucces_13(User *u)
{
  /* MAGE 2 3 */
  if (u->games_win_1 >= 100)
    u->succes[12] = '1';
}

void	Server::checkSucces_14(User *u)
{
  /* MAGE 2 4 */
  if (u->games_win_1 >= 250)
    u->succes[13] = '1';
}

void	Server::checkSucces_15(User *u)
{
  /* MAGE 2 5 */
  if (u->games_win_1 >= 1000)
    u->succes[14] = '1';
}

void	Server::checkSucces_16(User *u)
{
  /* INVOCATEUR 1 1 */
  if (u->games_played_2 >= 1)
    u->succes[15] = '1';
}

void	Server::checkSucces_17(User *u)
{
  /* INVOCATEUR 1 2 */
  if (u->games_played_2 >= 25)
    u->succes[16] = '1';
}

void	Server::checkSucces_18(User *u)
{
  /* INVOCATEUR 1 3 */
  if (u->games_played_2 >= 100)
    u->succes[17] = '1';
}

void	Server::checkSucces_19(User *u)
{
  /* INVOCATEUR 1 4 */
  if (u->games_played_2 >= 250)
    u->succes[18] = '1';
}

void	Server::checkSucces_20(User *u)
{
  /* INVOCATEUR 1 5 */
  if (u->games_played_2 >= 1000)
    u->succes[19] = '1';
}

void	Server::checkSucces_21(User *u){
  /* INVOCATEUR 2 1 */
  if (u->games_win_2 >= 1)
    u->succes[20] = '1';
}

void	Server::checkSucces_22(User *u)
{
  /* INVOCATEUR 2 2 */
  if (u->games_win_2 >= 25)
    u->succes[21] = '1';
}

void	Server::checkSucces_23(User *u)
{
  /* INVOCATEUR 2 3 */
  if (u->games_win_2 >= 100)
    u->succes[22] = '1';
}

void	Server::checkSucces_24(User *u)
{
  /* INVOCATEUR 2 4 */
  if (u->games_win_2 >= 250)
    u->succes[23] = '1';
}

void	Server::checkSucces_25(User *u)
{
  /* INVOCATEUR 2 5*/
  if (u->games_win_2 >= 1000)
    u->succes[24] = '1';
}

void	Server::checkSucces_26(User *u)
{
  /* ALL PLAYED 1 */
  if (u->games_played >= 1)
    u->succes[25] = '1';
}

void	Server::checkSucces_27(User *u)
{
  /* ALL PLAYED 2 */
  if (u->games_played >= 25)
    u->succes[26] = '1';
}

void	Server::checkSucces_28(User *u)
{
  /* ALL PLAYED 3 */
  if (u->games_played >= 100)
    u->succes[27] = '1';
}

void	Server::checkSucces_29(User *u)
{
  /* ALL PLAYED 4 */
  if (u->games_played >= 250)
    u->succes[28] = '1';
}

void	Server::checkSucces_30(User *u)
{
  /* ALL PLAYED 5 */
  if (u->games_played >= 1000)
    u->succes[29] = '1';
}

void	Server::checkSucces_31(User *u)
{
  /* ALL WIN 1 */
  if (u->games_win >= 1)
    u->succes[30] = '1';
}

void	Server::checkSucces_32(User *u)
{
  /* ALL WIN 2 */
  if (u->games_win >= 25)
    u->succes[31] = '1';
}

void	Server::checkSucces_33(User *u)
{
  /* ALL WIN 3 */
  if (u->games_win >= 100)
    u->succes[32] = '1';
}

void	Server::checkSucces_34(User *u)
{
  /* ALL WIN 4 */
  if (u->games_win >= 250)
    u->succes[33] = '1';
}

void	Server::checkSucces_35(User *u)
{
  /* ALL WIN 5 */
  if (u->games_win >= 1000)
    u->succes[34] = '1';
}

void	Server::checkSucces_36(User *u)
{
  /* TWICE PLAY 1 */
  if (u->games_played_1 >= 1 && u->games_played_2 >= 1)
    u->succes[35] = '1';
}

void	Server::checkSucces_37(User *u)
{
  /* TWICE PLAY 2 */
  if (u->games_played_1 >= 25 && u->games_played_2 >= 25)
    u->succes[36] = '1';
}

void	Server::checkSucces_38(User *u)
{
  /* TWICE PLAY 3 */
  if (u->games_played_1 >= 100 && u->games_played_2 >= 100)
    u->succes[37] = '1';
}

void	Server::checkSucces_39(User *u)
{
  /* TWICE PLAY 4 */
  if (u->games_played_1 >= 250 && u->games_played_2 >= 250)
    u->succes[38] = '1';
}

void	Server::checkSucces_40(User *u)
{
  /* TWICE PLAY 5 */
  if (u->games_played_1 >= 1000 && u->games_played_2 >= 1000)
    u->succes[39] = '1';
}

void	Server::checkSucces_41(User *u)
{
  /* TWICE WIN 1 */
  if (u->games_win_1 >= 1 && u->games_win_2 >= 1)
    u->succes[40] = '1';
}

void	Server::checkSucces_42(User *u)
{
  /* TWICE WIN 2 */
  if (u->games_win_1 >= 25 && u->games_win_2 >= 25)
    u->succes[41] = '1';
}

void	Server::checkSucces_43(User *u)
{
  /* TWICE WIN 3 */
  if (u->games_win_1 >= 100 && u->games_win_2 >= 100)
    u->succes[42] = '1';
}

void	Server::checkSucces_44(User *u)
{
  /* TWICE WIN 4 */
  if (u->games_win_1 >= 250 && u->games_win_2 >= 250)
    u->succes[43] = '1';
}

void	Server::checkSucces_45(User *u)
{
  /* TWICE WIN 5 */
  if (u->games_win_1 >= 1000 && u->games_win_2 >= 1000)
    u->succes[44] = '1';
}
