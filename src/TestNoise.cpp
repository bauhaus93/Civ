
int TestNoise(int octaves, double roughness, double scale){
    mt19937 rng{random_device{}()};
    while(true){
        Engine::Instance().ClearScene();
        SimplexNoise noise {};

        for(int i = 0; i < 1024/2; i++){
            for(int j = 0; j < 768/2; j++){
                double n = noise.GetOctavedNoise(i, j, octaves, roughness, scale);

                n = (n + 1) / 2;
                if(n > 0.5)
                    n = 1;
                else
                    n = 0;
                Engine::Instance().SetColor(RGBAColor{0, 0xFF * n, 0xFF * (1-n), 0xFF});
                Engine::Instance().DrawFillRect(Rect{i*2, j*2, 2, 2});


            }
        }
        Engine::Instance().ShowScene();
        Engine::Instance().SetWindowTitle("octaves: " + to_string(octaves) + " | roughness: " + to_string(roughness) + " | scale: " + to_string(scale));
        auto q = Engine::Instance().PollEvents();

        while (!q.empty()){
            Event& e = q.back();
            if(e.type == EventType::QUIT)
                return 0;
            q.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(750)));
    }
}
