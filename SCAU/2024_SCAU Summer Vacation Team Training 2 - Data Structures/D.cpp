// buxiangwanla
// 你紫名觉得是我的锅，那就是我的锅，为什么你知道吗？因为紫名说的话，就像是一个癌症晚期患者说的话一样。
// 他都已经这样了，你为什么不顺从他呢?你总要给人最后一段时间一个好的回忆吧，最后的时光里。
// 因为紫名这个段位很尴尬，紫名橙名再往上一点，grandmaster，可能说，欸，有点实力，能操作一下。
// 紫名往下，绿名，蓝名，啊，人家是纯属玩游戏的，因为太垃圾了，自己也知道自己没什么实力。
// 但紫名，上不去下不来的这个段位，他觉得，蓝名的人不配跟他一起玩儿，对吧？蓝名是最垃圾的。
// 但是呢他想上去，他又上不去，所以这个分段是最尴尬的，没办法，卡在这里了。
// 想操作，又操作不起来，掉下去吧，他又觉得不值得，对吧，我好不容易从蓝名打到紫名了，我为什么还要掉下去呢?
// 这个人说优越狗越说越起劲，为什么他会这么说?因为他是紫名。
// 他觉得你比我段位高，你说的任何话都是优越，我并不管你说的有没有道理。
// 我紫名，我最猛，我WF2017我上我能夺冠，那打比赛全是sb。你比我段位高你说话就是放屁，这就是这种人的想法。但是呢，他的想法是对的，为什么呢？
// 因为他癌症晚期。没办法，我同意，对不起，我优越了。可能是我膨胀了，不好意思啊，我膨胀了。我紫名是没操作，难道我就看不懂谁背锅吗？
// 不是，如果你看得懂的话，就不会在这里抬杠了，对吧。

// If you Blue Name think it's my fault, it's my fault. Do you know why? Because what Blue Name says is like something a terminal cancer patient would say.
// He's already like that. Why don't you just go along with it? You always have to give someone a good memory for the last period of time, right? In the last time.
// Because the blue name of this rating is very awkward, blue name purple name a little further up, master, may say, hey, a little strength, can operate a little.
// Blue name down, green name, ah, people are purely playing the game, because it is too trash, they also know that they do not have much strength.
// But the blue name, can't go up or down in this rating, he thinks, the green name of the person does not deserve to play with him, right? Green name is the most trash.
// But he wants to go up, he can not go up, so this rating is the most embarrassing, no way, stuck here.
// I want to solve, but I can not solve the problems, fall down, he also think it is not worth it, right, it is not easy for me to fight from the green name to the blue name, why do I have to fall down?
// This person said superior dog the more he said the more energized, why would he say so? Because he's blue.
// He thinks you are higher than me, anything you say is superior, I don't care if what you say makes sense or not.
// I'm not sure if there's any truth in what you're saying, but I'm not sure if there's any truth in what you're saying, and I'm not sure if there's any truth in what you're saying, and I'm not sure if there's any truth in what you're saying. But then, his idea is right, why?
// Because he has terminal cancer. No way, I agree. I'm sorry, I'm superior. Maybe I'm bloated. I'm sorry, I'm bloated. My blue name is no operation. Can't I see who's taking the fall?
// No, if you could see it, you wouldn't be here carrying the can, would you.
//
#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	std::vector adj(n + 1, std::vector<int>());
	for (int i = 1; i <= n - 1; i += 1) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	std::vector<int>siz(n + 1);
	auto dfs = [&](auto && self, int u, int par)->void{
		siz[u] += 1;
		for (const auto & v : adj[u]) {
			if (v == par) {
				continue;
			}
			self(self, v, u);
			siz[u] += siz[v];
		}
	};
	dfs(dfs, 1, 0);

	int ans = 0;
	for (const auto & v : adj[1]) {
		ans = std::max(ans, siz[v]);
	}

	std::cout << (n - ans) << "\n";

	return 0;
}