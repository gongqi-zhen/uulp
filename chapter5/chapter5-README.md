# chapter 5
接続をコントロールするーsttyを研究する

tcgetattr(3), tcsetattr(3)
stty(1), termios(4)
fcntl(2)
struct termios ( /usr/include/termios.h )

## ディスク接続の属性 (いくつかの属性があるが、ここでは２つを取り上げる。)
・バッファリング

ドライバ設定の変更手順
１、設定を取得する
２、設定を書き換える
３、設定を送り返す
//
#include <fcntl.h>
	int s;
	s = fcntl(fd, F_GETFL);
	s |= O_SYNC;
	result = fcntl(fd, F_SETFL, s);
	if (result == -1)
		perror("setting O_SYNC");
//

・追加モード (O_APPEND : auto append mode)
競合：race condition を防ぐための方法の一つ
 O_APPENDビットがセットされていると、write呼出には、自動的にファイルの末尾へのlseekが含まれるようになる。

//
lseek (fd, 0, SEEK_END);
write (fd, &rec, len);

#include <fcntl.h>
 int s;
 s = fcntl (fd, F_GETFL);
 s |= O_APPEND;
 result = fcntl (fd, F_SETFL, s);
 if (result == -1)
	 perror("setting APPEND");
 else
	 write(fd, &rec, l);

atomic operation
lseekとwriteは別個のシステムコールであり、カーネルは２つの処理の間の部分でプロセスに割り込みをかけることができる。
しかし、O_APPENDがセットされていると、カーネルはlseekとwriteをアトミックな処理にまとめる。
２つの処理が分割できない１つの単位に融合されるのである。

他
open(2)がサポートするそのほかのフラグ、 (O_CREAT, O_EXCL) これもある競合条件に対処するためのもの
ただし、意図としては良いが、ある重要な条件のもとでは適切に機能しない。link を使った方が信頼性が高い。
練習問題で例を示す

//


## 端末接続の属性

端末接続には、複雑なプロパティと処理ステップが含まれている。

ドライバ設定の変更手順
１、設定を取得する
２、設定を書き換える
３、設定を送り返す
//
#include <termios.h>
 struct termios settings;
 tcgetattr (fd, &settings);
 settings.c_lflag |= ECHO;
 tcsetattr (fd, TCSANOW, &settings );
//

端末接続のまとめ
端末は、人間がUnixプロセスと通信するために使うデバイスである。端末はキーボードを持ち、
プロセスはキーボードから文字を読み出す。また、端末はディスプレイを持ち、プロセスはディスプレイに文字を送り込む。
端末はデバイスなので、ディレクトリツリー内では特殊なファイルとして表現されて、通常は/devディレクトリにまとめられる。
端末とプロセスの間のデータ転送とデータ処理は、カーネルの一部である端末ドライバが行う。
このカーネルコードはバッファリング、編集、データ変換をサポートする。プログラムは、
tcgetattrとtcsetattrを使ってドライバの設定を読み出したり、書き換えたりすることができる。


1. stty は何をするのか

2. stty はどんな仕組みなのか


次は何か
　ディスクからのデータの読み出しはごく簡単だが、予測できない動きをする人間が入力した
内容の読み出しは難しい。人間の入力を読み出すプログラムは、端末ドライバの機能を使って
接続を制御することができる。次章では、対話型プログラムのためのプログラミングトピック
を詳しく取り上げる。
