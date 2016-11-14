DEFAULT:
	g++ judge.cpp -o judge -DLINUX
	sudo make install
install:
	cp ./judge /usr/bin/judge
uninstall:
	rm /usr/bin/judge
dev:
	make
	sudo make install
	rm ./judge
	rm ./.idea -rf
	git add .
	git commit -a -m "Commit"
	git push origin master
debug:
	g++ judge.cpp -o judge -DLINUX -DDEBUG
	sudo make install
