=====================================================================
		COS314 - Artificial Intelligence		     
=====================================================================

_____________
	     |
-u18014080   |
-Shaun Naude |
_____________|


1)How to test Program: 
	1.1) ->open a terminal in a GNU/linux system in the project dir.

	1.2) ->execute "$make run"
	      -> you will be prompted to enter a textfile.
	      -> In the testfiles folder there are a couple files that come from (http://elib.zib.de/pub/mp-testdata/tsp/tsplib/atsp).
	      -> feel free to add your own files aslong as they follow the website given above's format.

	1.3) ->when entering the textfile into the prompt make sure to add the dir eg. "testfile/input.txt"

	1.4) NOTE* when testing rbg443.txt the program will take ~8min to complete. All of the smaller testfiles 
	     should finish in under ~1min.

	1.5) The way the provided makefile works is it will place the executable in the bin folder once compiled.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

2)Heuristic Explanation
	2.1) for my h(n)=cost/depth
	      -> Essentially I am dividing the cost of travelling to the next node by the depth that the node would
                 be in the solution tree.
	      -> This heuristic essentially will favour nodes in the open list that are "closer" to the goal node
		 because it will divide cost by the depth of the node.
	      ->This heuristic is admissible because our worst case scenario is cost/1 , thus h(n) <= h*(n).

	2.2) For my g(n) I use the total length from the start node to the current.

	2.3 ) f(n) = g(n) + h(n) , I used f(n) to sort my open list, the node with the smallest f(n) will be the 
		next node added to the tree.





		
