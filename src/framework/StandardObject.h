#pragma once

class Program;

class StandardObject
{
protected:
    StandardObject();
    StandardObject(int priority);
	StandardObject(bool startsActivated, bool usesInput, bool usesUpdate, bool usesFixedUpdate, bool usesRenderer, bool usesImGui, bool usesDebugRenderer, int inputPriority, int updatePriority, int renderPriority, int imGuiPriority);
    
    //Program& m_Program;
    Program* m_Program;
    
    bool m_PauseImmune          { false };  //if this is true then normal pause will have no effect on this object, no object can escape truepause though 
    bool m_IsPersistentObject   { false };  //if this is true then this object wont be destroyed when switching scenes
	bool m_ShouldDestruct       { false };  //should this object be destroyed at the end of the loop
	
	//bools that tell which loops are used by this object
    bool m_UsesInput;           //tells if this object use the input loop
    bool m_UsesUpdate;          //tells if this object use the update loop
    bool m_UsesFixedUpdate;     //tells if this object use the fixedUpdate loop
    bool m_UsesRenderer;        //tells if this object use the render loop
    bool m_UsesDebugRenderer;   //tells if this object use the debugRender loop
    bool m_UsesImGui;           //tells if this object use the ImGui loop

    unsigned int m_InputPriority;       //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int m_UpdatePriority;      //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int m_FixedUpdatePriority; //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int m_RenderPriority;      //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int m_ImGuiPriority;       //lower goes first, the object created first goes first if priority numbers are the same

	bool m_ShouldBeActive;	//says if the object should be active or not
	bool m_IsActiveState;	//is the actual active/inactive state of the object

public:
    ~StandardObject();

    void AddToLists();      //adds this object to its appropriate list

    void RemoveFromLists(); //removes this object from lists that it is in if the corresponding bool is on false
	
    /**
     * this is called when the object gets created
     * after the constructor but before the awake and the loops
     */
    virtual void Start();

    /**
     * this is called when the object gets set to active
     * if the object is created active awake will run right after the start method but before the loops
     * if the object is created inactive awake will run when the object is set to active which happens right after the program loops
     * Awake will run every time the object goes from inactive to active
     */
    virtual void Awake();

    /**
     * this is called when the object gets set to inactive
     * Sleep will run every time the object goes from active to inactive which happens right after the program loops
     */
    virtual void Sleep();

    virtual void Destroy();

    virtual void Input(double deltaTime);
	
    virtual void Update(double deltaTime);
	
    virtual void Render(double deltaTime);
	
    virtual void ImGuiRender(double deltaTime);
	
    virtual void DebugRender(double deltaTime);

    bool GetUsesInput()          const{ return m_UsesInput; }
    bool GetUsesUpdate()         const{ return m_UsesUpdate; }
    bool GetUsesFixedUpdate()    const{ return m_UsesFixedUpdate; }
    bool GetUsesRenderer()       const{ return m_UsesRenderer; }
    bool GetUsesDebugRenderer()  const{ return m_UsesDebugRenderer; }
    bool GetUsesImGui()          const{ return m_UsesImGui; }

    unsigned int GetInputPriority()         const{ return m_InputPriority; }   //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int GetUpdatePriority()        const{ return m_UpdatePriority; }   //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int GetFixedUpdatePriority()   const{ return m_FixedUpdatePriority; }   //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int GetRenderPriority()        const{ return m_RenderPriority; }   //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int GetImGuiPriority()         const{ return m_ImGuiPriority; }   //lower goes first, the object created first goes first if priority numbers are the same
	
	bool GetShouldDestruct()     const { return m_ShouldDestruct; }
	bool IsShouldBeActive()      const { return m_ShouldBeActive; }
	bool IsActiveState()		 const { return m_IsActiveState; }
    bool IsPauseImmune()         const { return m_PauseImmune; }
    bool IsPersistentObject()    const { return m_IsPersistentObject; }
	
    
	void SetShouldBeActive   (bool b) { m_ShouldBeActive = b; }
	void SetActiveState      (bool b) { m_IsActiveState  = b; }
    
private:
};
