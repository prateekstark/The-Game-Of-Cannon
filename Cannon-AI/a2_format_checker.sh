cd 2017CS10360_StarkBot

bash compile.sh

# Run the code
python server.py 10000 -n 8 -m 8 -NC 2 -TL 2 -LOG server.log &
server_pid=$!
python client.py 0.0.0.0 10000 RandomPlayer.py > player1 &
client1_pid=$!
python client.py 0.0.0.0 10000 run.sh > player2 &
client2_pid=$!

# Wait for completion
wait $client1_pid
wait $client2_pid
wait $server_pid

score=`grep -o "Player 2 SCORE : [0-9.]*" server.log | awk -F" " '{print $5}'`
echo $roll_number"\t"$score >> ../results.tsv
