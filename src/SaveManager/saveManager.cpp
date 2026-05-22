class SaveManager{
    private:
        static SaveManager* _instance;

    public:
        static SaveManager* Instance(){
            if (_instance == 0){
                _instance = new SaveManager;
            }
            return _instance;
        }
};

SaveManager* SaveManager::_instance=0;